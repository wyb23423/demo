/// <reference types="node" />
import { Next, Handler } from '../typings';
import { IncomingMessage, ServerResponse } from 'http';
import { HTTPMethods, HTTPMethodName } from '../utils/htpp-methods';
export default class Route extends HTTPMethods<Route, Handler, void> {
    path?: string | undefined;
    private stack;
    constructor(path?: string | undefined);
    dispatch(req: IncomingMessage, res: ServerResponse, done: Next): void;
    setHTTPMethos(method: HTTPMethodName, handler: Handler): void;
}
