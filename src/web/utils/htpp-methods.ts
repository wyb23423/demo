import { METHODS } from 'http';
import { Handler } from '../typings';

type Method<T> = (pathOrHandler: string | Handler, handler?: Handler) => T;

export type HTTPMethodName = 'get' | 'post' | 'put' | 'head' | 'delete' | 'options' | 'trace' | 'copy' | 'lock' | 'mkcol' | 'move' | 'purge' | 'propfind' | 'proppatch' | 'unlock' | 'report' | 'mkactivity' | 'checkout' | 'merge' | 'notify' | 'subscribe' | 'unsubscribe' | 'patch' | 'search' | 'connect' | 'm-search';

// export default function AddHTTPMethods(
//     fn: (method: HTTPMethodName, handler: Handler, path: string) => any
// ) {
//     // tslint:disable-next-line:ban-types
//     return (target: Function) => {
//         METHODS.forEach(method => {
//             method = method.toLocaleLowerCase();

//             Reflect.set(target.prototype, method, function(pathOrHandler: string | Handler, handler?: Handler) {
//                 handler = typeof pathOrHandler === 'function' ? pathOrHandler : handler;
//                 if (handler) {
//                     fn.call(this, <HTTPMethodName>method, handler, <string>pathOrHandler);
//                 } else {
//                     console.warn('处理函数为空!');
//                 }

//                 return this;
//             });
//         });
//     };
// }


export class HTTPMethods<T> {
    public get!: Method<T>;
    public post!: Method<T>;
    public put!: Method<T>;
    public head!: Method<T>;
    public delete!: Method<T>;
    public options!: Method<T>;
    public trace!: Method<T>;
    public copy!: Method<T>;
    public lock!: Method<T>;
    public mkcol!: Method<T>;
    public move!: Method<T>;
    public purge!: Method<T>;
    public propfind!: Method<T>;
    public proppatch!: Method<T>;
    public unlock!: Method<T>;
    public report!: Method<T>;
    public mkactivity!: Method<T>;
    public checkout!: Method<T>;
    public merge!: Method<T>;
    public notify!: Method<T>;
    public subscribe!: Method<T>;
    public unsubscribe!: Method<T>;
    public patch!: Method<T>;
    public search!: Method<T>;
    public connect!: Method<T>;
    public 'm-search'!: Method<T>;

    constructor(fn: (method: HTTPMethodName, handler: Handler, path: string) => any) {
        METHODS.forEach(method => {
            method = method.toLocaleLowerCase();

            const proto = Object.getPrototypeOf(this);
            Reflect.set(proto, method, (pathOrHandler: string | Handler, handler?: Handler) => {
                handler = typeof pathOrHandler === 'function' ? pathOrHandler : handler;
                if (handler) {
                    fn.call(this, <HTTPMethodName>method, handler, <string>pathOrHandler);
                } else {
                    console.warn('处理函数为空!');
                }

                return this;
            });
        });
    }
}
