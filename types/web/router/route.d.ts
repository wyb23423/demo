import { Next, Handler, CRequest, CResponse } from '../typings';
import { HTTPMethods, HTTPMethodName } from '../utils/htpp-methods';
export default class Route extends HTTPMethods<Route, Handler, void> {
    path?: string | undefined;
    private stack;
    constructor(path?: string | undefined);
    dispatch(req: CRequest, res: CResponse, done: Next): void;
    setHTTPMethos(method: HTTPMethodName, handler: Handler): void;
}
