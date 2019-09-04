/// <reference types="node" />
import Route from './route';
import { HTTPMethods, HTTPMethodName } from '../utils/htpp-methods';
import { Handler, Next, ErrorHandler } from '../typings';
import { IncomingMessage, ServerResponse } from 'http';
export default class Router extends HTTPMethods<Router> {
    private routes;
    all(path: string, handler: Handler): this;
    use(pathOrHandler: string | Handler | ErrorHandler, handler?: Handler | ErrorHandler): void | this;
    route(path: string): Route;
    dispatch(req: IncomingMessage, res: ServerResponse, done: Next): void;
    setHTTPMethos(method: HTTPMethodName, handler: Handler, path: string): void;
}
