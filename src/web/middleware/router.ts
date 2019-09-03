/**
 * 路由级中间件
 */
import BaseRouter from '../router';
import { IncomingMessage, ServerResponse } from 'http';
import { Next } from '../typings';

type Dispatch = (req: IncomingMessage, res: ServerResponse, done: Next) => void;

export default function Router(): BaseRouter & Dispatch {
    const router = new BaseRouter();

    return new Proxy(router.dispatch.bind(router), {
        get(t: any, k: string) {
            const val = Reflect.get(router, k);
            return typeof val === 'function' ? val.bind(router) : val;
        }
    });
}
