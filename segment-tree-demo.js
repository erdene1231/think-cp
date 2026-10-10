// A small learning example: four leaves and a recursive inclusive sum query.
export function segmentTreeDemo(lang, typeset) {
    const en = lang === 'en';
    const make = (tag, text, cls) => {
        const el = document.createElement(tag);
        if (text !== undefined) el.textContent = text;
        if (cls) el.className = cls;
        return el;
    };
    const wrap = make('aside', undefined, 'segment-demo');
    wrap.append(make('h4', en ? 'Try the recursive tree' : 'Recursive tree дээр өөрөө туршаарай'));
    wrap.append(make('p', en
        ? 'Change a value or the query endpoints. Green intervals are taken whole, yellow ones split, and gray ones contribute zero.'
        : 'Утга эсвэл query-ийн заагийг өөрчил. Ногоон хэсгийг бүхлээр нь авна, шар хэсгийг задална, саарал хэсгээс тэг авна.'));
    const form = make('form', undefined, 'segment-demo-controls');
    const values = [2, 1, 3, 4].map((value, i) => {
        const label = make('label', '$a[' + i + ']$');
        const input = make('input');
        Object.assign(input, {type: 'number', min: '-1000', max: '1000', step: '1', value: String(value), required: true});
        input.setAttribute('aria-label', 'a[' + i + ']');
        label.append(input);
        form.append(label);
        return input;
    });
    const boundary = (name, value) => {
        const label = make('label', '$' + name + '$');
        const input = make('select');
        input.setAttribute('aria-label', name);
        for (let i = 0; i < 4; i++) {
            const option = make('option', String(i));
            option.value = String(i);
            input.append(option);
        }
        input.value = String(value);
        label.append(input);
        form.append(label);
        return input;
    };
    const left = boundary('l', 1), right = boundary('r', 3);
    const button = make('button', en ? 'Build and query' : 'Build ба query хийх');
    button.type = 'submit';
    form.append(button);
    const output = make('div', undefined, 'segment-demo-output');
    output.setAttribute('aria-live', 'polite');
    wrap.append(form, output);
    function draw() {
        output.replaceChildren();
        const a = values.map(input => Number(input.value));
        const ql = Number(left.value), qr = Number(right.value);
        if (ql > qr) {
            output.append(make('p', en ? 'Choose a left endpoint no greater than the right endpoint.' : 'Зүүн зааг баруун заагаасаа ихгүй байх ёстой.'));
            return;
        }
        const nodes = [], tree = [];
        function build(v, l, r, depth) {
            const item = {v, l, r, depth, state: 'idle'};
            nodes.push(item);
            if (l === r) {
                tree[v] = a[l];
            } else {
                const mid = Math.floor((l + r) / 2);
                build(2 * v, l, mid, depth + 1);
                build(2 * v + 1, mid + 1, r, depth + 1);
                tree[v] = tree[2 * v] + tree[2 * v + 1];
            }
        }
        const trace = [];
        function query(v, l, r) {
            const item = nodes.find(node => node.v === v);
            if (qr < l || r < ql) {
                item.state = 'excluded';
                trace.push('$[' + l + ',' + r + ']$: ' + (en ? 'no overlap, return $0$.' : 'давхцахгүй, $0$ буцаана.'));
                return 0;
            }
            if (ql <= l && r <= qr) {
                item.state = 'covered';
                trace.push('$[' + l + ',' + r + ']$: ' + (en ? 'full coverage, return $' : 'бүтнээр багтсан, $') + tree[v] + '$.');
                return tree[v];
            }
            item.state = 'partial';
            trace.push('$[' + l + ',' + r + ']$: ' + (en ? 'partial coverage, visit both children.' : 'хэсэгчлэн, хоёр child руу орно.'));
            const mid = Math.floor((l + r) / 2);
            return query(2 * v, l, mid) + query(2 * v + 1, mid + 1, r);
        }
        build(1, 0, 3, 0);
        const ans = query(1, 0, 3);
        const diagram = make('div', undefined, 'segment-demo-tree');
        diagram.setAttribute('aria-label', en ? 'Recursive sum tree' : 'Recursive sum tree');
        for (let depth = 0; depth < 3; depth++) {
            const row = make('div', undefined, 'segment-demo-level');
            for (const item of nodes.filter(node => node.depth === depth)) {
                const box = make('div', undefined, 'segment-demo-node ' + item.state);
                box.append(make('span', '$[' + item.l + ',' + item.r + ']$'));
                box.append(make('strong', '$\\mathrm{sum}=' + tree[item.v] + '$'));
                row.append(box);
            }
            diagram.append(row);
        }
        output.append(diagram, make('p', (en ? 'Answer: ' : 'Хариу: ') + '$\\mathrm{query}(' + ql + ',' + qr + ')=' + ans + '$', 'segment-demo-answer'));
        const list = make('ol');
        for (const line of trace) list.append(make('li', line));
        output.append(list);
    }
    form.onsubmit = event => {
        event.preventDefault();
        if (!form.reportValidity()) return;
        void typeset([output], () => draw()).catch(() => {});
    };
    draw();
    return wrap;
}
