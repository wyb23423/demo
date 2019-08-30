import { Handler } from '../typings';
declare type Method<T> = (pathOrHandler: string | Handler, handler?: Handler) => T;
export declare type HTTPMethodName = 'get' | 'post' | 'put' | 'head' | 'delete' | 'options' | 'trace' | 'copy' | 'lock' | 'mkcol' | 'move' | 'purge' | 'propfind' | 'proppatch' | 'unlock' | 'report' | 'mkactivity' | 'checkout' | 'merge' | 'notify' | 'subscribe' | 'unsubscribe' | 'patch' | 'search' | 'connect' | 'm-search';
export declare class HTTPMethods<T> {
    get: Method<T>;
    post: Method<T>;
    put: Method<T>;
    head: Method<T>;
    delete: Method<T>;
    options: Method<T>;
    trace: Method<T>;
    copy: Method<T>;
    lock: Method<T>;
    mkcol: Method<T>;
    move: Method<T>;
    purge: Method<T>;
    propfind: Method<T>;
    proppatch: Method<T>;
    unlock: Method<T>;
    report: Method<T>;
    mkactivity: Method<T>;
    checkout: Method<T>;
    merge: Method<T>;
    notify: Method<T>;
    subscribe: Method<T>;
    unsubscribe: Method<T>;
    patch: Method<T>;
    search: Method<T>;
    connect: Method<T>;
    'm-search': Method<T>;
    constructor(fn: (method: HTTPMethodName, handler: Handler, path: string) => any);
}
export {};
