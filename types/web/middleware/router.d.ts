/// <reference types="node" />
/**
 * 路由级中间件
 */
import BaseRouter from '../router';
import { IncomingMessage, ServerResponse } from 'http';
import { Next } from '../typings';
declare type Dispatch = (req: IncomingMessage, res: ServerResponse, done: Next) => void;
export default function Router(): BaseRouter & Dispatch;
export {};
