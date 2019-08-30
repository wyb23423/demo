import Route from './route';
import Layer from './layer';
import { HTTPMethods, HTTPMethodName } from '../utils/htpp-methods';
import { Handler, Next } from '../typings';
import { IncomingMessage, ServerResponse, METHODS } from 'http';
import { SKIP_ROUTER, SKIP_ROUTE } from '../constant';

export default class Router extends HTTPMethods<Router> {
    private routes: Layer[] = [];

    constructor() {
        super(
            (method: HTTPMethodName, handler: Handler, path: string) => {
                const route = this.route(path);
                route[method] && route[method](handler);
            }
        );
    }

    public all(path: string, handler: Handler) {
        const route = this.route(path);
        METHODS.forEach(method => route[<HTTPMethodName>method.toLocaleLowerCase()](handler));

        return this;
    }

    // 通过路径创建路由容器并创建路由
    public route(path: string) {
        const route = new Route();

        const pathType = typeof path;
        if (pathType !== 'string') {
            console.error('路由路径必须是字符串' + `(${pathType})`);
        } else {
            this.routes.push(new Layer(route.dispatch.bind(route), path));
        }

        return route;
    }

    public dispatch(req: IncomingMessage, res: ServerResponse, done: Next) {
        let index: number = 0;

        const next = (err?: string | Error) => {
            // 跳过当前路由系统
            if (err === SKIP_ROUTER) {
                return done();
            }

            if (err === SKIP_ROUTE) {
                err = '';
            }

            const layer = this.routes[index++];
            if (!layer) {
                return done(err);
            }

            if (req.url && layer.match(req.url)) {
                if (err) {
                    layer.doError(err, req, res, next);
                } else {
                    layer.doRequest(req, res, next);
                }
            } else {
                next(err);
            }
        };

        next();
    }
}
