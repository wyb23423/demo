import createApplication from './web/index';
import Router from './web/middleware/router';

const app = createApplication();

const router1 = Router();
router1.use('/:g', (_1: any, _2: any, next: any) => next());

const router2 = Router();
router2.use('/:id', router1);

app.use('/test', router2);

app.listen(8082);
