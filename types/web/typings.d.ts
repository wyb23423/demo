/// <reference types="node" />
import { IncomingMessage, ServerResponse } from 'http';
import { ParsedUrlQuery } from 'querystring';
export interface CResponse extends IncomingMessage {
    query: ParsedUrlQuery;
    originUrl: string;
    params: ParsedUrlQuery;
    init(): void;
}
export interface CRequest extends ServerResponse {
    send(msg: any): void;
}
export declare type Handler = (req: CResponse, res: CRequest, next: Next) => void;
export declare type ErrorHandler = (err: any, req: CResponse, res: CRequest, next: Next) => void;
export declare type Next = (err?: string | Error) => void;
