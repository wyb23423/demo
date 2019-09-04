import { Handler, ErrorHandler } from './typings';
import { HTTPMethods, HTTPMethodName } from './utils/htpp-methods';
export default class Aplication extends HTTPMethods<Aplication> {
    private router;
    all(path: string, handler: Handler): this;
    use(pathOrHandler: string | Handler | ErrorHandler, handler?: Handler | ErrorHandler): this;
    listen(port?: number, hostname?: string, backlog?: number, listeningListener?: () => void): this;
    set(): void;
    static(): void;
    setHTTPMethos(method: HTTPMethodName, handler: Handler, path: string): void;
    private handle;
}
