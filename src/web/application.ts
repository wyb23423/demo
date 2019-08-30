import { createServer, METHODS, IncomingMessage, ServerResponse } from 'http';
import { HTTPMethods, HTTPMethodName } from './utils/htpp-methods';
import Router from './router/index';
import { Handler } from './typings';

export default class Aplication extends HTTPMethods<Aplication> {
    private router = new Router();

    constructor() {
        super(
            (method: HTTPMethodName, handler: Handler, path: string) =>
                this.router[method] && this.router[method](path, handler)
        );
    }

    public all(path: string, handler: Handler) {
        this.router.all(path, handler);
        return this;
    }

    public listen(port?: number, hostname?: string, backlog?: number, listeningListener?: () => void) {
        createServer(this.handle.bind(this)).listen(port, hostname, backlog, listeningListener);

        return this;
    }

    public use() {
        //
    }

    public set() {
        //
    }

    public static() {
        //
    }

    private handle(req: IncomingMessage, res: ServerResponse) {
        req.method = req.method && req.method.toLowerCase();

        this.router.dispatch(req, res, (err: any) => {
            res.writeHead(404, { 'Content-Type': 'text/plain' });
            res.end(err || 'Not Found: ' + req.method + ' ' + req.url);
        });
    }
}
