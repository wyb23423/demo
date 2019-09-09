/// <reference types="node" />
import { Handler, ErrorHandler, Next, CResponse, CRequest } from '../typings';
import { ParsedUrlQuery } from 'querystring';
export default class Layer {
    private handler;
    private path?;
    method?: string | undefined;
    isMiddleware: boolean;
    private length;
    private keys;
    private regexp?;
    constructor(handler: Handler | ErrorHandler, path?: string | undefined, method?: string | undefined);
    match(path: string): {
        params: ParsedUrlQuery;
        url: string;
    } | undefined;
    doRequest(req: CRequest, res: CResponse, next: Next): void;
    doError(err: any, req: CRequest, res: CResponse, next: Next): void;
}
