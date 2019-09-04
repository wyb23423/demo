/// <reference types="node" />
import { Handler, ErrorHandler, Next } from '../typings';
import { IncomingMessage, ServerResponse } from 'http';
export default class Layer {
    private handler;
    private path?;
    method?: string | undefined;
    isMiddleware: boolean;
    private keys;
    private regexp?;
    constructor(handler: Handler | ErrorHandler, path?: string | undefined, method?: string | undefined);
    match(path: string): boolean;
    doRequest(req: IncomingMessage, res: ServerResponse, next: Next): void;
    doError(err: any, req: IncomingMessage, res: ServerResponse, next: Next): void;
}
