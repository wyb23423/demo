import { queryMultiple } from './index';

export function createBaseAndZoneData() {
    const bases = [];
    const zones = [];

    for (let i = 1; i <= 1; i++) {
        const groupCode = i.toString(16).padStart(4, '0').toUpperCase();
        const data = [
            [503, 2117],
            [2885, 2117],
            [2885, 700],
            [503, 700],
        ];

        bases.push(...[23, 15, 30, 25].map((c, j) => (
            [
                'A00000' + c, groupCode,
                '192.168.1.' + c,
                +(j === 0),
                j ? '0.00000000320189580915' : '0.00050025131130394492',
                ...data[j],
                100,
                `demo_${i}_${j}`
            ]
        )));

        zones.push(
            [parsePosition2(data), 1, groupCode, null, 4, 'group_' + i, 0], // 分组区域
            // 切换区域
            [
                parsePosition2([[2785, 800], [2985, 800], [2985, 1000], [2785, 1000]]),
                1, groupCode, 1000, 1, 'switch_' + i, 0
            ]
        );
    }

    return [[bases], [zones]];
}

export function parsePosition1(data: number[][]) {
    return JSON.stringify(data.map(v => ({ x: v[0], y: v[1], z: 1 })));
}

export function parsePosition2(data: number[][]) {
    return JSON.stringify({ coordinates: data.map(v => ({ xaixs: v[0], yaixs: v[1], zaixs: 1 })) });
}

export default async function setBaseAndZone() {
    console.log('start....');

    await queryMultiple(['pos_base_station', 'pos_zone'].map(v => `truncate table ${v}`));

    console.log('truncate end....');

    const baseSql = 'insert into pos_base_station (base_no, group_code, ip, main, time_correction_value, coordx, coordy, coordz, name) values ?';
    const zoneSql = 'insert into pos_zone (position, enable, base_no_1, base_no_2, mode) values ?';
    await queryMultiple([baseSql, zoneSql], createBaseAndZoneData());

    console.log('end....');
}
