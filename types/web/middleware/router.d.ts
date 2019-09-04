/**
 * 路由级中间件
 */
import { CResponse, Next, CRequest } from '../typings';
import BaseRouter from '../router';
declare type Dispatch = (req: CResponse, res: CRequest, done: Next) => void;
export default function Router(): BaseRouter & Dispatch & {
    isRouter: true;
};
export {};
