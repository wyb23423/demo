import Route from './route';
import { HTTPMethods, HTTPMethodName } from '../utils/htpp-methods';
import { Handler, Next, ErrorHandler, CResponse, CRequest } from '../typings';
export default class Router extends HTTPMethods<Router> {
    private routes;
    all(path: string, handler: Handler): this;
    use(pathOrHandler: string | Handler | ErrorHandler, handler?: Handler | ErrorHandler): void | this;
    route(path: string): Route;
    dispatch(req: CResponse, res: CRequest, done: Next): void;
    setHTTPMethos(method: HTTPMethodName, handler: Handler, path: string): void;
}
