import { createHmac } from 'crypto';

const SALT = 'wyb960426';
const LEN = 15;

interface Config {
    number?: boolean;
    lower?: boolean;
    upper?: boolean;
    symbol?: boolean;
}

export function doGenPasswd(domain: string, account: string, must: Config = {}) {
    return genPasswd('password', SALT + domain + account, must);
}

export default function genPasswd(key: string, raw: string, must: Config = {}) {
    const hmac = createHmac('sha1', key);
    hmac.update(raw);

    let passwd = hmac.digest('base64').substring(0, LEN);
    if (!must.symbol) {
        passwd = passwd.replace('+', '0').replace('/', '1');
    }

    const lastCode = passwd.codePointAt(LEN - 1) || 0;

    if (must.number && !/\d/.test(passwd)) {
        passwd += '0123456789'[lastCode % 10];
    }
    if (must.lower && !/[a-z]/.test(passwd)) {
        passwd += 'abcdefghijklmnopqrstuvwxyz'[lastCode % 26];
    }
    if (must.upper && !/A-Z/.test(passwd)) {
        passwd += 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'[lastCode % 26];
    }

    must.symbol && (passwd += '!@#$%^&*()_+=-{}[]><?/\\'[lastCode % 23]);

    return passwd;
}
