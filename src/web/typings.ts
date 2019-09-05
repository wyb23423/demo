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

export type Handler = (req: CResponse, res: CRequest, next: Next) => void;
export type ErrorHandler = (err: any, req: CResponse, res: CRequest, next: Next) => void;

export type Next = (err?: string | Error) => void;


