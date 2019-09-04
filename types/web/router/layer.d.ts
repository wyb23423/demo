import { Handler, ErrorHandler, Next, CResponse, CRequest } from '../typings';
export default class Layer {
    private handler;
    private path?;
    method?: string | undefined;
    isMiddleware: boolean;
    private keys;
    private regexp?;
    constructor(handler: Handler | ErrorHandler, path?: string | undefined, method?: string | undefined);
    match(path: string): boolean;
    doRequest(req: CResponse, res: CRequest, next: Next): void;
    doError(err: any, req: CResponse, res: CRequest, next: Next): void;
}
