/* eslint-disable no-unused-vars */
/* eslint-disable @typescript-eslint/no-explicit-any */
/* eslint-disable @typescript-eslint/no-unused-vars */
// @ts-expect-error
export interface EventName<T extends any[] = any[]> extends Symbol {}

export default class Events {
  /**
   * 为一个对象添加 发布-订阅 功能
   */
  public static mixTo<T extends object>(target: T) {
    Events.assgin(target);
    Reflect.set(target, '_$events', new Map<EventName, Set<Function>>());

    return target as T & Events;
  }

  private static assgin(target: Record<string | symbol, any>) {
    const keys = Object.getOwnPropertyNames(Events.prototype);
    keys.forEach((k) => {
      if (k !== 'constructor') {
        target[k] = Reflect.get(Events.prototype, k);
      }
    });
  }

  constructor(private readonly _$events = new Map<EventName, Set<Function>>()) {
    //
  }

  public on<T extends any[]>(evt: EventName<T>, handler: (...args: T) => unknown) {
    if (typeof handler !== 'function') {
      return this;
    }

    const set = this._$events.get(evt) ?? new Set();
    set.add(handler);
    this._$events.set(evt, set);

    return this;
  }

  public off(evt: EventName, handler?: Function) {
    if (!handler) {
      this._$events.delete(evt);
    } else {
      const set = this._$events.get(evt);
      set?.delete(handler);
    }

    return this;
  }

  public emit<T extends any[]>(evt: EventName<T>, ...args: T) {
    return this.trigger(evt, ...args);
  }

  public once<T extends any[]>(evt: EventName<T>, handler: (...args: T) => unknown) {
    if (typeof handler === 'function') {
      const fn = (...args: T) => {
        handler(...args);
        this.off(evt, fn);
      };

      this.on(evt, fn);
    }

    return this;
  }

  public trigger<T extends any[]>(evt: EventName<T>, ...args: T) {
    const set = this._$events.get(evt);
    set?.forEach((fn) => fn(...args));

    return this;
  }
}
