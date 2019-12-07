const isValidEmail = (email: string): boolean => /^[\w-\.]+@[a-zA-Z]+\.com$/.test(email);
console.log(isValidEmail('john-doe31@gmail.com'));
console.log(isValidEmail('jane.austen_691@dnarifle.com'));
