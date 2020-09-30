const { parse, createVisitor } = require('java-ast');
const fs = require('fs')
const path = require('path')

function visitor(source, path) {
    const stream = fs.createWriteStream(path.replace(/java$/, 'd.ts'))

    stream.write('declare interface ')

    const ast = parse(source.toString())
    let hasExtends = false
    createVisitor({
        visitClassDeclaration(ctx) {
            stream.write(ctx.IDENTIFIER().text)

            if (hasExtends = !!ctx.EXTENDS()) {
                stream.write(' extends ')
            } else {
                stream.write(' {\n')
            }
        },
    }).visit(ast)

    // 不知道怎么出现了属性(类型还是一样的)重复, 重载???
    const set = new Set()

    let filedType = ''
    createVisitor({
        visitClassOrInterfaceType(ctx) {
            const type = ctx.text
                .replace(/Integer|Long|BigDecimal|Double|Short|LocalDateTime/g, 'number')
                .replace(/String|LocalDate/g, 'string')
                .replace('Boolean', 'boolean')
                .replace('Map', 'Record')
                .replace('List', 'Array')

            if (hasExtends) {
                stream.write(type + ' {\n')
                hasExtends = false
            } else {
                filedType = type
            }
        },
        visitPrimitiveType(ctx) {
            if (ctx.BOOLEAN()) {
                filedType = 'boolean'
            } else if (ctx.CHAR()) {
                filedType = 'string'
            } else {
                filedType = 'number'
            }
        },
        visitVariableDeclaratorId(ctx) {
            if (set.has(ctx.text)) {
                return
            }

            stream.write(`  ${ctx.text}: ${filedType};\n`)
            set.add(ctx.text)
        },
    }).visit(ast)

    stream.write('}\n')
    stream.end()
}

function readDir(dir) {
    fs.promises.readdir(dir)
        .then(files => files.forEach(f => {
            const file = path.resolve(dir, f)
            if (fs.statSync(file).isDirectory()) {
                readDir(file)
            } else if (file.endsWith('.java')) {
                fs.promises.readFile(file).then(data => visitor(data, file))
            }
        }))
}

readDir(path.resolve(__dirname, 'java'))
