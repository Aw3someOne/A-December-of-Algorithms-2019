import { createInterface } from 'readline';

const rl = createInterface({
	input: process.stdin,
	output: process.stdout,
});

const vowels = new Set(['a', 'e', 'i', 'o', 'u']);
const isVowel = (char: string) => vowels.has(char.toLocaleLowerCase());
const isConsonant = (char: string) => !isVowel(char);

function calculateScore(str: string, fn: (char: string) => boolean): number {
	let score = 0;
	for (let i = 0; i < str.length; i++)
		if (fn(str[i]))
			score += str.length - i;
	return score;
}

rl.question('Enter string: ', (answer: string) => {
	const a = calculateScore(answer, isVowel);
	const b = calculateScore(answer, isConsonant);
	if (a === b)
		console.log(`A and B are tied with ${a} points.`);
	else
		console.log(`The winner is ${a > b ? 'A' : 'B'} with ${Math.max(a, b)} points.`);
	rl.close();
});
