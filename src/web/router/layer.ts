import { Handler, ErrorHandler, Next, CResponse, CRequest } from '../typings';
import * as pathToRegexp from 'path-to-regexp';
import { ParsedUrlQuery } from 'querystring';

export default class Layer {
    public isMiddleware: boolean = false;

    private length: number = 0;
    private keys: pathToRegexp.Key[] = [];
    private regexp?: RegExp;

    constructor(
        private handler: Handler | ErrorHandler,
        private path?: string,
        public method?: string
    ) {
        if (path) {
            this.regexp = pathToRegexp(path, this.keys);
            this.length = path.split('/').length;
        }
    }

    // 路由匹配
    public match(path: string) {
        if (!this.path) {
            return { params: {}, url: path };
        }

        // ===========================中间件
        if (this.isMiddleware) {
            const names = path.split('/');

            if (this.length < names.length) {
                names.length = this.length;
                path = names.join('/');
            }
        }

        // =======================匹配并获取参数
        const res = this.regexp && path.match(this.regexp);
        if (res) {
            const params: ParsedUrlQuery = {};
            for (let i = 1; i < res.length; i++) {
                const name = this.keys[i - 1].name;

                let val = params[name];
                if (val) {
                    val = Array.isArray(val) ? val : [val];
                    val.push(res[i]);
                } else {
                    val = res[i];
                }

                params[name] = val;
            }

            return { params, url: path };
        }
    }

    // 执行处理函数
    public doRequest(req: CResponse, res: CRequest, next: Next) {
        try {
            const parent = req.parentUrl;
            // 路由级中间件
            if (this.isMiddleware && (<any>this.handler).isRouter) {
                req.parentUrl = parent + req.url;
                req.url = req.originUrl.substr(parent.length + req.url.length);
            }

            (<Handler>this.handler)(req, res, next);

            req.url = req.originUrl.substr(parent.length);
            req.parentUrl = parent;
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
