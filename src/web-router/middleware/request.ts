import { IncomingMessage } from 'http';
import { parse } from 'url';
import { CRequest } from '../typings';

const request: CRequest = Object.assign(
    Object.create(IncomingMessage.prototype),
    {
        query: {},
        originUrl: '',
        parentUrl: '',
        params: {}
    }
);

// tslint:disable-next-line:space-before-function-paren
request.init = function (this: CRequest) {
    const url = this.url || '/';
    const pathInfo = parse(url, true);

    this.query = pathInfo.query;
    this.url = this.originUrl = pathInfo.pathname || '/';

    this.method = (this.method || '').toLowerCase();
};

export default request;
