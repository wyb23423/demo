import { queryMultiple } from './index';


function createData() {
    const bases = [];
    const zones = [];

    for (let i = 1; i <= 100; i++) {
        const groupCode = i.toString(16).padStart(4, '0').toUpperCase();
        const data = [
            [503, 2117],
            [2885, 2117],
            [503, 700],
            [2885, 700],
        ];

        bases.push(...[23, 15, 25, 30].map((c, j) => (
            [
                'A00000' + c, groupCode,
                '192.168.1.' + c,
                +(j === 0),
                j ? '0.00000000320189580915' : '0.00050025131130394492',
                ...data[j],
                100, 4, 4, 22
            ]
        )));

        zones.push(
            [
                JSON.stringify({ coordinates: data.map(v => ({ xaxis: v[0], yaxis: v[1], zaxis: 1 })) }),
                1, groupCode, null, 4
            ], // 分组区域
            // 切换区域
            [
                JSON.stringify({
                    coordinates: [
                        { xaxis: 2785, yaxis: 800, zaxis: 1 },
                        { xaxis: 2985, yaxis: 800, zaxis: 1 },
                        { xaxis: 2985, yaxis: 1000, zaxis: 1 },
                        { xaxis: 2785, yaxis: 1000, zaxis: 1 }
                    ]
                }),
                1, groupCode, 1000, 1
            ]
        );
    }

    return [[bases], [zones]];
}

export default async function setBaseAndZone() {
    console.log('start....');

    await queryMultiple(['pos_base_station', 'pos_zone'].map(v => `truncate table ${v}`));

    console.log('truncate end....');

    const baseSql = 'insert into pos_base_station (base_no, group_code, ip, main, time_correction_value, coordx, coordy, coordz, group_base_size, min_base_size, algorithm_type) values ?';
    const zoneSql = 'insert into pos_zone (position, enable, base_no_1, base_no_2, mode) values ?';
    await queryMultiple([baseSql, zoneSql], createData());

    console.log('end....');
}
