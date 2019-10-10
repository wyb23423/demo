import { queryMultiple } from './index';

function createBaseData() {
    const baseValues = [];
    for (let i = 1; i <= 100; i++) {
        const data = [
            [503, 2117],
            [2885, 2117],
            [503, 1441],
            [2885, 1441],
        ];

        baseValues.push(...[23, 15, 25, 30].map((c, j) => (
            ['A00000' + c, i.toString(16).padStart(4, '0').toUpperCase(), '192.168.1.' + c, +(j === 0), j ? '0.00000000320189580915' : '0.00050025131130394492', ...data[j], 100, '测试'].map(v => v == null ? v : v + '')
        )));
    }

    return baseValues;
}

export function createTagData() {
    const values = [];
    for (let i = 1; i <= 500; i++) {
        values.push(...new Array(100).fill(0).map((v, j) => {
            return [
                ((j + 1).toString(16).padStart(4, '0') + i.toString(16).padStart(4, '0')).toUpperCase(),
                '1',
                `test_${i}_${j}`,
                '/image/PVZ2ekZ8BIxyXFkuskI72aofkR5TV4.png'
            ];
        }));
    }

    return values;
}

function createGroupData() {
    return new Array(100).fill(1).map((v, i) => [(i + v).toString(16).padStart(4, '0').toUpperCase(), 4, 4, 1, 22]);
}

export default async function test() {
    console.log('start....');

    await queryMultiple(['pos_base_station', 'pos_tag', 'pos_base_group'].map(v => `truncate table ${v}`));

    console.log('truncate end....');

    const baseSql = 'insert into `pos_base_station` (`base_no`, `group_code`, `ip`, `main`, `time_correction_value`, `coordx`, `coordy`, `coordz`, `name`) values ?';
    const tagSql = 'insert into `pos_tag` (`tag_no`, `type`, `name`, `photo`) values ?';
    const groupSql = 'insert into `pos_base_group` (`group_code`, `group_base_size`, `min_base_size`, `map_id`, `algorithm_type`) values ?';
    await queryMultiple(
        [baseSql, tagSql, groupSql],
        [
            [createBaseData()],
            [createTagData()],
            [createGroupData()]
        ]
    );

    console.log('end....');
}
