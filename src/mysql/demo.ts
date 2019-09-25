import { queryMultiple } from './index';

function createBaseData() {
    const baseValues = [];
    for (let i = 1; i <= 2; i++) {
        const data = [
            [503, 2117],
            [2885, 2117],
            [503, 1441],
            [2885, 1441],
        ];

        baseValues.push(...[23, 15, 25, 30].map((c, j) => (
            ['A00000' + c, i.toString(16).padStart(4, '0').toUpperCase(), '192.168.1.' + c, +(j === 0), 22, j ? '0.00000000320189580915' : '0.00050025131130394492', ...data[j], 100, 4, 3, '测试', '2018-09-25 09:47:52', null, null, '测试', '22', null, null, null, null, null, null, null, null].map(v => v == null ? v : v + '')
        )));
    }

    return baseValues;
}

function createTagData() {
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

export default function test() {
    const baseSql = 'INSERT INTO `pos_base_station` (`base_no`, `group_code`, `ip`, `main`, `algorithm_type`, `time_correction_value`, `coordx`, `coordy`, `coordz`, `group_base_size`, `min_base_size`, `name`, `install_time`, `description`, `upload_type`, `location`, `zone`, `owner`, `work`, `lose_rate`, `alarm`, `create_user`, `create_time`, `update_user`, `update_time`) VALUES ?';

    const tagSql = 'INSERT INTO `pos_tag` (`tag_no`, `type`, `name`, `photo`) VALUES ?';

    queryMultiple([baseSql, tagSql], [[createBaseData()], [createTagData()]]);
}
