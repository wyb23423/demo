import { IncomingMessage, ServerResponse } from 'http';
import { ParsedUrlQuery } from 'querystring';

export interface CRequest extends IncomingMessage {
    url: string;
    query: ParsedUrlQuery;
    originUrl: string;
    parentUrl: string;
    params: ParsedUrlQuery;

    init(): void;
}

export interface CResponse extends ServerResponse {
    send(msg: any): void;
}

export type Handler = (req: CRequest, res: CResponse, next: Next) => void;
export type ErrorHandler = (err: any, req: CRequest, res: CResponse, next: Next) => void;

export type Next = (err?: string | Error) => void;


