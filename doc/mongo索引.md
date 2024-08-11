## mongo索引

````javascript
let tables = [
    "article",
    "page_header",
    "view",
    "tag_dictionary",
    "statistic"
];

// 为每个表创建公共索引
tables.forEach(table => {
    // id
    db[table].createIndex({
        id : 1
    }, {unique: true})
    
    // created_at
    db[table].createIndex({
        created_at : -1
    })
    
    // updated_at
    db[table].createIndex({
        updated_at: -1
    })
})

// 主键表索引
db.primary_key.createIndex({
    table_name: 1
}, {
    unique: true
})

// 文章表索引
db.article.createIndex({
    article_title: "text"
})
db.article.createIndex({
    article_description: "text"
})
````

