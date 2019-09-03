import { HTTPMethods } from './utils/htpp-methods';
import { Handler, ErrorHandler } from './typings';
export default class Aplication extends HTTPMethods<Aplication> {
    private router;
    constructor();
    all(path: string, handler: Handler): this;
    use(pathOrHandler: string | Handler | ErrorHandler, handler?: Handler | ErrorHandler): this;
    listen(port?: number, hostname?: string, backlog?: number, listeningListener?: () => void): this;
    set(): void;
    static(): void;
    private handle;
}
