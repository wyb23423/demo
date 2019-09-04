import { METHODS } from 'http';
import { Handler } from '../typings';

type Method<T, D, K> = (pathOrHandler: D, handler: K) => T;

export type HTTPMethodName = 'get' | 'post' | 'put' | 'head' | 'delete' | 'options' | 'trace' | 'copy' | 'lock' | 'mkcol' | 'move' | 'purge' | 'propfind' | 'proppatch' | 'unlock' | 'report' | 'mkactivity' | 'checkout' | 'merge' | 'notify' | 'subscribe' | 'unsubscribe' | 'patch' | 'search' | 'connect' | 'm-search';

export class HTTPMethods<T = any, D = string, K = Handler> {
    public get!: Method<T, D, K>;
    public post!: Method<T, D, K>;
    public put!: Method<T, D, K>;
    public head!: Method<T, D, K>;
    public delete!: Method<T, D, K>;
    public options!: Method<T, D, K>;
    public trace!: Method<T, D, K>;
    public copy!: Method<T, D, K>;
    public lock!: Method<T, D, K>;
    public mkcol!: Method<T, D, K>;
    public move!: Method<T, D, K>;
    public purge!: Method<T, D, K>;
    public propfind!: Method<T, D, K>;
    public proppatch!: Method<T, D, K>;
    public unlock!: Method<T, D, K>;
    public report!: Method<T, D, K>;
    public mkactivity!: Method<T, D, K>;
    public checkout!: Method<T, D, K>;
    public merge!: Method<T, D, K>;
    public notify!: Method<T, D, K>;
    public subscribe!: Method<T, D, K>;
    public unsubscribe!: Method<T, D, K>;
    public patch!: Method<T, D, K>;
    public search!: Method<T, D, K>;
    public connect!: Method<T, D, K>;
    public 'm-search'!: Method<T, D, K>;

    public setHTTPMethos(method: HTTPMethodName, handler: Handler, path: string) {
        throw new ReferenceError('Method HTTPMethods.prototype.setHTTPMethos is not defined');
    }
}

METHODS.forEach(method => {
    method = method.toLocaleLowerCase();

    Reflect.set(
        HTTPMethods.prototype,
        method,
        // tslint:disable-next-line:only-arrow-functions
        function(this: HTTPMethods, pathOrHandler: string | Handler, handler?: Handler) {
            handler = typeof pathOrHandler === 'function' ? pathOrHandler : handler;
            if (handler) {
                this.setHTTPMethos(<HTTPMethodName>method, handler, <string>pathOrHandler);
            } else {
                console.warn('处理函数为空!');
            }

            return this;
        }
    );
});
