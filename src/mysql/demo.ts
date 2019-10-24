import { queryMultiple } from './index';
import { createBaseAndZoneData } from './demo2';

export function createTagData() {
    const values = [];
    for (let i = 1; i <= 10000; i++) {
        values.push(...new Array(1).fill(0).map((v, j) => {
            return [
                ((j + 1).toString(16).padStart(4, '0') + i.toString(16).padStart(4, '0')).toUpperCase(),
                '1',
                `test_${i}_${j}`,
                '/image/PVZ2ekZ8BIxyXFkuskI72aofkR5TV4.png',
                0
            ];
        }));
    }

    return values;
}

function createGroupData() {
    return new Array(100).fill(1).map((v, i) => [(i + v).toString(16).padStart(4, '0').toUpperCase(), 4, 4, 0, 22]);
}

export default async function test() {
    console.log('start....');

    await queryMultiple(['pos_base_station', 'pos_tag', 'pos_group', 'pos_zone'].map(v => `truncate table ${v}`));

    console.log('truncate end....');

    const baseSql = 'insert into pos_base_station (id, group_id, ip, main, time_correction_value, coordx, coordy, coordz, name) values ?';
    const zoneSql = 'insert into pos_zone (position, enable, group_id_1, group_id_2, mode, name, map_id) values ?';
    const tagSql = 'insert into pos_tag (id, type, name, icon, height) values ?';
    const groupSql = 'insert into pos_group (id, size, min, map_id, algorithm_type) values ?';

    await queryMultiple(
        [baseSql, zoneSql, tagSql, groupSql],
        [
            ...createBaseAndZoneData(),
            [createTagData()],
            [createGroupData()]
        ]
    );

    console.log('end....');
}
