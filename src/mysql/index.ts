import mysql from 'mysql';
import databaseConfig from './mysql.config';

export async function query(sql: string, params: any) {
    const connection = mysql.createConnection(databaseConfig);

    try {
        await connect(connection);
    } catch (e) {
        return Promise.reject(e);
    }

    let data: [any, mysql.FieldInfo[] | undefined];
    try {
        data = await doQuery(connection, sql, params);
    } catch (e) {
        return Promise.reject(e);
    }

    return end(connection).then(() => data);
}

export async function queryMultiple(sqls: string[], values: any[] = []) {
    const connection = mysql.createConnection(databaseConfig);

    try {
        await connect(connection);
    } catch (e) {
        return Promise.reject(e);
    }

    let data: Array<[any, mysql.FieldInfo[] | undefined]> = [];
    try {
        data = await Promise.all(sqls.map((v, i) => doQuery(connection, v, values[i])));
    } catch (e) {
        return Promise.reject(e);
    }

    return end(connection).then(() => data);
}

function connect(connection: mysql.Connection) {
    return new Promise((resolve, reject) => {
        connection.connect((err: mysql.MysqlError | null) => {
            if (err) {
                return reject(err);
            }

            resolve();
        });
    });
}

function end(connection: mysql.Connection) {
    return new Promise((resolve, reject) => {
        connection.end((err: mysql.MysqlError | null) => {
            if (err) {
                console.log('关闭数据库连接失败！');
                connection.destroy();
                return reject(err);
            }

            resolve();
        });
    });
}

function doQuery(
    connection: mysql.Connection,
    sql: string,
    params: any
): Promise<[any, mysql.FieldInfo[] | undefined]> {
    return new Promise((resolve, reject) => {
        connection.query(sql, params, (err: mysql.MysqlError | null, results?: any, fields?: mysql.FieldInfo[]) => {
            if (err) {
                console.log('数据操作失败');
                connection.destroy();
                return reject(err);
            }

            resolve([results, fields]);
        });
    });
}
