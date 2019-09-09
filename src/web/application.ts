import { Handler, ErrorHandler, CResponse, CRequest } from './typings';

import { createServer, IncomingMessage, ServerResponse } from 'http';
import { HTTPMethods, HTTPMethodName } from './utils/htpp-methods';
import Router from './router/index';
import response from './middleware/request';

export default class Aplication extends HTTPMethods<Aplication> {
    private router = new Router();

    public all(path: string, handler: Handler) {
        this.router.all(path, handler);
        return this;
    }

    public use(pathOrHandler: string | Handler | ErrorHandler, handler?: Handler | ErrorHandler) {
        this.router.use(pathOrHandler, handler);
        return this;
    }

    public listen(port?: number, hostname?: string, backlog?: number, listeningListener?: () => void) {
        createServer((req: IncomingMessage, res: ServerResponse) => {
            Object.setPrototypeOf(req, response);
            this.handle(<CRequest>req, <CResponse>res);
        })
            .listen(port, hostname, backlog, listeningListener);
        return this;
    }

    public set() {
        //
    }

    public static() {
        //
    }

    public setHTTPMethos(method: HTTPMethodName, handler: Handler, path: string) {
        this.router[method] && this.router[method](path, handler);
    }

    private handle(req: CRequest, res: CResponse) {
        req.init();

        this.router.dispatch(req, res, (err: any) => {
            res.writeHead(404, { 'Content-Type': 'text/plain' });
            res.end(err || 'Not Found: ' + req.method + ' ' + req.originUrl);
        });
    }
}
