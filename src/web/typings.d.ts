import { IncomingMessage, ServerResponse } from 'http';

declare type Handler = (req: IncomingMessage, res: ServerResponse, next: Next) => void;
declare type ErrorHandler = (err: any, req: IncomingMessage, res: ServerResponse, next: Next) => void;

declare type Next = (err?: string | Error) => void;
