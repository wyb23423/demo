/// <reference types="node" />
import { IncomingMessage, ServerResponse } from 'http';
import { ParsedUrlQuery } from 'querystring';
export interface CResponse extends IncomingMessage {
    url: string;
    query: ParsedUrlQuery;
    originUrl: string;
    parentUrl: string;
    params: ParsedUrlQuery;
    init(): void;
}
export interface CRequest extends ServerResponse {
    send(msg: any): void;
}
export declare type Handler = (req: CRequest, res: CResponse, next: Next) => void;
export declare type ErrorHandler = (err: any, req: CRequest, res: CResponse, next: Next) => void;
export declare type Next = (err?: string | Error) => void;
