import { Next, Handler, CRequest, CResponse } from '../typings';
import Layer from './layer';
import { SKIP_ROUTE, SKIP_ROUTER } from '../constant';
import { HTTPMethods, HTTPMethodName } from '../utils/htpp-methods';

export default class Route extends HTTPMethods<Route, Handler, void> {
    private stack: Layer[] = [];

    constructor(public path?: string) {
        super();
    }

    public dispatch(req: CResponse, res: CRequest, done: Next) {
        let index: number = 0;

        const next = (err?: string | Error) => {
            // 跳过当前路由
            if (err === SKIP_ROUTE) {
                return done();
            }

            // 跳过当前路由系统
            if (err === SKIP_ROUTER) {
                return done(err);
            }

            const layer = this.stack[index++];
            if (!layer) {
                return done(err);
            }

            if (err) {
                layer.doError(err, req, res, next);
            } else if (layer.method === req.method) {
                layer.doRequest(req, res, next);
            } else {
                next(err);
            }
        };

        next();
    }

    public setHTTPMethos(method: HTTPMethodName, handler: Handler) {
        this.stack.push(new Layer(handler, undefined, method));
    }
}
