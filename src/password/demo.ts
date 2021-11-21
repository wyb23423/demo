import { createHmac } from 'crypto';

const SALT = 'wyb960426';
const LEN = 15;
const SYMBOL = '!@#$%^&*()_+=-{}[]><?/\\';

interface Config {
    number?: boolean;
    lower?: boolean;
    upper?: boolean;
    symbol?: boolean;
    len?: number;
}

export function doGenPasswd(domain: string, account: string, config: Config = {}) {
    return genPasswd('password', SALT + domain + account, config);
}

export default function genPasswd(key: string, raw: string, config: Config = {}) {
    const hmac = createHmac('sha1', key);
    hmac.update(raw);

    let length = config.len || LEN;
    if (length <= 0) {
        length = LEN;
    }

    let passwd = hmac.digest('base64').substring(0, length);
    const lastCode = passwd.codePointAt(length - 1) || 0;

    if (config.number && !/\d/.test(passwd)) {
        passwd += '0123456789'[lastCode % 10];
        passwd = passwd.slice(1);
    }
    if (config.lower && !/[a-z]/.test(passwd)) {
        passwd += 'abcdefghijklmnopqrstuvwxyz'[lastCode % 26];
        passwd = passwd.slice(1);
    }
    if (config.upper && !/A-Z/.test(passwd)) {
        passwd += 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'[lastCode % 26];
        passwd = passwd.slice(1);
    }

    if (!config.symbol) {
        passwd = passwd.replace('+', '0').replace('/', '1');
    } else if (!new RegExp(`[${SYMBOL}]`).test(passwd)) {
        passwd += SYMBOL[lastCode % 23];
        passwd = passwd.slice(1);
    }

    return passwd;
}
