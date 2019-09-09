/**
 * 路由级中间件
 */
import { CResponse, Next, CRequest } from '../typings';
import BaseRouter from '../router';

type Dispatch = (req: CRequest, res: CResponse, done: Next) => void;

export default function Router(): BaseRouter & Dispatch & { isRouter: true } {
    const router = new BaseRouter();

    return new Proxy(router.dispatch.bind(router), {
        get(t: any, k: string) {
            if (k === 'isRouter') {
                return true;
            }

            const val = Reflect.get(router, k);
            return typeof val === 'function' ? val.bind(router) : val;
        }
    });
}
