# Software Security

## Client summary

The client, Artemis Financial, wanted me to perform security analysis on their web software and make security recommendations in regard to cryptography.

## What I did particularly well

I think the most important thing I did particularly well was updating dependencies to automatically resolve all of the vulnerabilities in the code. This is a lot harder to do in production systems as code can quickly become convoluted, especially with major semver changes, but it was easy in the context of the given code. It's important to code securely to future-proof against vulnerabilities. For example, writing as little code as possible that relies on a library means that if the library were to have a vulnerability, only a small section would be affected--or none at all, if you don't make use of that vulnerable code from the library. In regard to what it adds to the company's overall wellbeing, it is like a stamp saying "yes, we are secure, you can trust us more."

## What about the process of working through the vulnerability assessment I found challenging or helpful

It was a little tedious writing out all of the CVEs and linking them, but I think it helped in the long run, especially since I got a good grade for doing my research. The OWASP Dependency-Check Project is a very useful tool that saved so much time performing manual searches for CVEs. The only challenge I ran into was figuring out why suppressing a CVE didn't make it disappear from the dependency check, but it just made it show up under the suppressed category.

## How I approached the need to increase layers of security, and what techniques or strategies I would use in the future to assess vulnerabilities and determine mitigation techniques

Doing regular dependency checks during the development process is the main strategy I can think of, but another is to only use a library or external dependency if it's an absolute must, like abstracting a very tedious process.

## How I ensured the code and software application were functional and secure, and how after refactoring the code, I checked to see whether I introduced new vulnerabilities

As I just mentioned, regular dependency checks. Nothing I did introduced vulnerabilities, but I double-checked.

## What resources, tools, or coding practices I employed that I might find helpful in future assignments or tasks

Unsurprisingly, regular dependency checks is the main thing I picked up from this. the OWASP Dependency-Check Project is a very important tool that I will use from now on to ensure code security.

## What from this particular assignment I might want to showcase to a future employer

The ability to design a software security report and perform vulnerability assessments.

