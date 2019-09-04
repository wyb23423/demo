import { IncomingMessage } from 'http';
import { parse } from 'url';
import { ParsedUrlQuery } from 'querystring';

export interface CResponse extends IncomingMessage {
    query: ParsedUrlQuery;
    originUrl: string;
    params: ParsedUrlQuery;

    init(): void;
}

const req: CResponse = Object.assign(
    Object.create(IncomingMessage),
    {
        query: {},
        originUrl: '',
        params: {}
    }
);
req.init = function (this: CResponse) {
    const url = this.url || '/';
    const pathInfo = parse(url, true);

    this.query = pathInfo.query;
    this.url = this.originUrl = pathInfo.pathname || '/';
    this.method = (this.method || '').toLowerCase();
};

export default req;
