import { HTTPMethods } from './utils/htpp-methods';
import { Handler } from './typings';
export default class Aplication extends HTTPMethods<Aplication> {
    private router;
    constructor();
    all(path: string, handler: Handler): this;
    listen(port?: number, hostname?: string, backlog?: number, listeningListener?: () => void): this;
    use(): void;
    set(): void;
    static(): void;
    private handle;
}
