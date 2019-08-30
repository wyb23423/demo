/// <reference types="node" />
import { Handler, ErrorHandler, Next } from '../typings';
import { IncomingMessage, ServerResponse } from 'http';
export default class Layer {
    private handler;
    method?: string | undefined;
    private keys;
    private regexp;
    constructor(handler: Handler | ErrorHandler, path?: string, method?: string | undefined);
    match(path: string): boolean;
    doRequest(req: IncomingMessage, res: ServerResponse, next: Next): void;
    doError(err: any, req: IncomingMessage, res: ServerResponse, next: Next): void;
}
