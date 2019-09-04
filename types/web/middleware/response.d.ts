/// <reference types="node" />
import { IncomingMessage } from 'http';
import { ParsedUrlQuery } from 'querystring';
export interface CResponse extends IncomingMessage {
    query: ParsedUrlQuery;
    originUrl: string;
    params: ParsedUrlQuery;
    init(): void;
}
declare const req: CResponse;
export default req;
