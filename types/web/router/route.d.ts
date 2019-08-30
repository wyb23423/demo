/// <reference types="node" />
import { Next } from '../typings';
import { IncomingMessage, ServerResponse } from 'http';
import { HTTPMethods } from '../utils/htpp-methods';
export default class Route extends HTTPMethods<Route> {
    path?: string | undefined;
    private stack;
    constructor(path?: string | undefined);
    dispatch(req: IncomingMessage, res: ServerResponse, done: Next): void;
}
