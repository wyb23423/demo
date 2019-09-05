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
    doRequest(req: CResponse, res: CRequest, next: Next): void;
    doError(err: any, req: CResponse, res: CRequest, next: Next): void;
}
