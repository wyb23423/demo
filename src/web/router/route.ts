import { Next, Handler } from '../typings';
import Layer from './layer';
import { IncomingMessage, ServerResponse } from 'http';
import { SKIP_ROUTE, SKIP_ROUTER } from '../constant';
import { HTTPMethods } from '../utils/htpp-methods';

export default class Route extends HTTPMethods<Route> {
    private stack: Layer[] = [];

    constructor(public path?: string) {
        super((method: string, handler: Handler) => this.stack.push(new Layer(handler, undefined, method)));
    }

    public dispatch(req: IncomingMessage, res: ServerResponse, done: Next) {
        let index: number = 0;
        console.log(this.stack);
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
}
