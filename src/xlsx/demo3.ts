import xlsx from 'node-xlsx';
import fs from 'fs';

const mapData = {
    id: 1,
    name: 'demo map',
};
const groupData = {
    id: 'A0000001',
    size: 4,
    min: 4,
    map: { ...mapData }
};
const testDataItem = {
    id: '0001',
    name: 'test',
    ip: '127.0.0.1',
    coordx: 0,
    group: { ...groupData },
    arr1: [
        {
            name: 'arr1',
            map: { ...mapData },
            arr2: [
                { id: 1 },
                { id: 2 },
                { id: 3 }
            ]
        },
        {
            name: 'arr2',
            map: { ...mapData },
            arr2: [
                { id: 4 }
            ]
        }
    ]
};

const testData = new Array(10).fill(1).map((v, i) => ({ ...testDataItem, id: '000' + i }));
const comparison: Record<string, string> = {
    id: 'ID',
    name: '名称',
    ip: 'ip',
    coordx: 'x坐标',
    map: '地图',
    group: '分组',
    arr: '测试数组',
    size: '最大基站数',
    min: '最小基站数'
};
export default function run() {
    const tableMap = createTable('base', testData, new Map());
    const worksheets: any[] = [];
    tableMap.forEach((v, k) => worksheets.push({
        name: k,
        data: removal(v.data),
        options: { '!merges': v.range }
    }));

    const buffer = xlsx.build(worksheets);
    const file = './src/xlsx/demo3.xlsx';
    fs.unlink(file, () => fs.writeFile(file, buffer, err => console.log(err)));
}

// ========================================================================
function createTable(
    table: string,
    source: Array<Record<string, any>>,
    tableMap: TableMap
) {
    const { range, data } = tableMap.get(table) || { range: [], data: [] };
    data.length || data.push(...createHead(source, range));
    source.map(item => data.push(getDataItem(Object.entries(item), tableMap)));
    tableMap.set(table, { range, data });

    return tableMap;
}

// =================================================创建表头
function createHead(source: Array<Record<string, any>>, range: any[]) {
    const data: any[][] = [];
    const { columns, deep } = getColumns(source);
    for (let i = 0; i < deep; i++) {
        data.push([]);
    }

    const fn = (column: ColumnItem, r: number) => {
        const row = data[r];
        const currCIndex = row.length; // 本次数据填充数据开始的列索引
        if (column.children) { // 存在子元素，有跨列
            const len = getMaxWidth(column.children);
            range.push({
                s: { r, c: currCIndex },
                e: { r, c: currCIndex + len - 1 }
            });
            row.push(column.title, ...new Array(len - 1).fill(null));

            // 用子元素填充下一行数据
            column.children.forEach(v => fn(v, r + 1));
        } else { // 没有子元素, 可能存在跨行
            row.push(column.title); // 当前行
            // 用null填充跨行数据
            for (let i = r + 1; i < deep; i++) {
                data[i].push(null);
            }
            range.push({
                s: { r, c: currCIndex },
                e: { r: deep - 1, c: currCIndex }
            });
        }
    };
    columns.forEach(v => fn(v, 0));

    return data;
}
function getColumns(source: Array<Record<string, any>>, deep: number = 1) {
    const columns: any[] = [];
    Object.entries(source[0]).forEach(([k, v]) => {
        if (typeof v === 'object' && v !== null) {
            if (!Array.isArray(v)) {
                const data = getColumns([v], deep + 1);
                columns.push({
                    title: comparison[k],
                    children: data.columns
                });

                deep = Math.max(deep, data.deep);
            }
        } else {
            columns.push({ title: comparison[k] });
        }
    });

    return { columns, deep };
}
function getMaxWidth(column: ColumnItem[]): number {
    return column.reduce((a, b) => a + (b.children ? getMaxWidth(b.children) : 1), 0);
}
// ======================================================================================

// 创建用于填充数据表的数据
function getDataItem(
    source: Array<[string, Record<string, any>]>,
    tableMap: TableMap
) {
    const data: any[] = [];
    source.forEach(([k, v]) => {
        if (typeof v === 'object' && v !== null) {
            if (Array.isArray(v)) {
                v.length && createTable(k, v, tableMap);
            } else {
                data.push(...getDataItem(Object.entries(v), tableMap));
            }
        } else {
            data.push(v);
        }
    });

    return data;
}
// 数据去重
function removal(data: any[][]) {
    const result: any[][] = [];
    data.forEach(v => {
        const flag = result.some(item => {
            if (item.length !== v.length) {
                return false;
            }

            for (let i = 0; i < v.length; i++) {
                if (v[i] !== item[i]) {
                    return false;
                }
            }

            return true;
        });

        if (!flag) {
            result.push(v);
        }
    });

    return result;
}


interface ColumnItem {
    title: string;
    children?: ColumnItem[];
}

type TableMap = Map<string, { range: any[], data: any[][] }>;
