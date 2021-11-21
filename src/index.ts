// import createApplication from './web-router/index';
// import Router from './web-router/middleware/router';

// const app = createApplication();

// const router1 = Router();
// router1.use('/:g', (_1: any, _2: any, next: any) => next());

// const router2 = Router();
// router2.use('/:id', router1);

// app.use('/test', router2);

// app.listen(8082);

import { doGenPasswd } from './password/demo';
console.log(doGenPasswd('www.blackshark.com', '残梦', { len: 11 }));
