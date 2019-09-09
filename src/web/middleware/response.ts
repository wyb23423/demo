import { ServerResponse } from 'http';
import { CResponse, HeaderVal } from '../typings';

const response: CResponse = Object.create(ServerResponse.prototype);

// tslint:disable:space-before-function-paren
response.send = function (this: CResponse, body: any, encoding?: string) {
    this.writeHead(this.statusCode, this.statusMessage);
    return new Promise(resolve => encoding ? this.end(body, encoding, resolve) : this.end(body, resolve));
};
response.json = function (this: CResponse, body: IAnyObject, encoding?: string) {
    return this.set('Content-Type', 'application/json').send(JSON.stringify(body), encoding);
};
response.status = function (this: CResponse, code: number) {
    this.statusCode = code;

    return this;
};
response.set = function (this: CResponse, nameOrVal: string | IAnyObject<HeaderVal>, val?: HeaderVal) {
    let data: IAnyObject<HeaderVal> = {};
    if (typeof nameOrVal === 'string') {
        if (val == null) {
            return this;
        }

        data[nameOrVal] = val;
    } else {
        data = nameOrVal;
    }

    for (const [k, v] of Object.entries(data)) {
        this.setHeader(k, v);
    }

    return this;
};

export default response;
