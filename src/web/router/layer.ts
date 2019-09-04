import { Handler, ErrorHandler, Next, CResponse, CRequest } from '../typings';
import * as pathToRegexp from 'path-to-regexp';

export default class Layer {
    public isMiddleware: boolean = false;

    private keys: pathToRegexp.Key[] = [];
    private regexp?: RegExp;

    constructor(
        private handler: Handler | ErrorHandler,
        private path?: string,
        public method?: string
    ) {
        path && (this.regexp = pathToRegexp(path, this.keys));
    }

    // 路由匹配
    public match(path: string) {
        // ===========================中间件
        if (this.isMiddleware) {
            return false;
        }

        // ===============================
        if (this.regexp) {
            return this.regexp.test(path);
        }

        return true;
    }

    // 执行处理函数
    public doRequest(req: CResponse, res: CRequest, next: Next) {
        try {
            (<Handler>this.handler)(req, res, next);
        } catch (e) {
            next(e);
        }
    }

    // 执行错误处理中间件
    public doError(err: any, req: CResponse, res: CRequest, next: Next) {
        const fn = this.handler;

        // 不是错误处理中间件
        if (fn.length !== 4) {
            return next(err);
        }

        try {
            (<ErrorHandler>fn)(err, req, res, next);
        } catch (e) {
            next(e);
        }
    }
}
