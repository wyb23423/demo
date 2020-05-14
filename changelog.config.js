module.exports = {
    "list": [
        "test",
        "feat",
        "fix",
        "chore",
        "docs",
        "refactor",
        "style",
        "ci",
        "perf",
        "build",
        "revert"
    ],
    "maxMessageLength": 72,
    "questions": [
        "type",
        "scope",
        "subject",
        "lerna"
    ],
    "types": {
        "chore": {
            "description": "构建过程或辅助工具的更改",
            "emoji": "🤖",
            "value": "chore"
        },
        "ci": {
            "description": "与CI相关的更改",
            "emoji": "🎡",
            "value": "ci"
        },
        "docs": {
            "description": "文档变更",
            "emoji": "✏️",
            "value": "docs"
        },
        "feat": {
            "description": "新功能",
            "emoji": "🎸",
            "value": "feat"
        },
        "fix": {
            "description": "bug修复",
            "emoji": "🐛",
            "value": "fix"
        },
        "perf": {
            "description": "性能优化",
            "emoji": "⚡️",
            "value": "perf"
        },
        "refactor": {
            "description": "重构(既不是增加feature，也不是修复bug)",
            "emoji": "💡",
            "value": "refactor"
        },
        "revert": {
            "description": "回退",
            "emoji": "☜",
            "value": "revert"
        },
        "style": {
            "description": "代码格式(不影响代码运行的变动)",
            "emoji": "💄",
            "value": "style"
        },
        "test": {
            "description": "增加测试",
            "emoji": "💍",
            "value": "test"
        },
        "build": {
            "description": "打包",
            "emoji": "₪",
            "value": "build"
        }
    }
};