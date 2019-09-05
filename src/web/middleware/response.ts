import { IncomingMessage } from 'http';
import { parse } from 'url';
import { CResponse } from '../typings';

const response: CResponse = Object.assign(
    Object.create(IncomingMessage.prototype),
    {
        query: {},
        originUrl: '',
        parentUrl: '',
        params: {}
    }
);

// tslint:disable-next-line:space-before-function-paren
response.init = function (this: CResponse) {
    const url = this.url || '/';
    const pathInfo = parse(url, true);

    this.query = pathInfo.query;
    this.url = this.originUrl = pathInfo.pathname || '/';

    this.method = (this.method || '').toLowerCase();
};

export default response;
