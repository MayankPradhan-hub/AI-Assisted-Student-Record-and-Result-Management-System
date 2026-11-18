tool used:Chatgpt
prompt given:
I am a first-semester B.Tech CSE student building a console-based Student Record Management System in C. I need a simple "Academic Advisor" feature that gives advice based on a student's CGPA (scale 0 to 10, average of up to 8 SGPAs).
Please suggest:
1. Four performance categories (for example Excellent, Good, Needs Improvement, Requires Immediate Attention) with a CGPA range for each.
2. A short advice message (one line) for each category.
3. One extra idea for advice using the SGPA values, such as when the latest SGPA is lower than the previous one.
Do not write any code. Keep it simple enough to implement with if-else statements in C.

Response:
A simple four-category system would work well for a first-semester C project:
| CGPA Range | Category | Advice Message |
|---|---|---|
| **8.5 – 10.0** | Excellent | “Excellent performance! Keep up the consistency and aim even higher.” |
| **7.0 – 8.49** | Good | “Good progress! Stay consistent and focus on improving weaker subjects.” |
| **5.0 – 6.99** | Needs Improvement | “Your performance can improve. Review difficult topics and practice regularly.” |
| **0.0 – 4.99** | Requires Immediate Attention | “Academic attention is needed. Focus on fundamentals and seek help from teachers.” |
These ranges are simple and non-overlapping, so they're straightforward to implement using an if-else if-else structure.
Extra idea using SGPA trend
Compare the latest SGPA with the previous SGPA:
- Latest SGPA lower than previous → “Your recent performance has declined. Review what affected this semester and focus on improvement.”
- Latest SGPA higher than previous → “Your performance is improving. Keep following your current study strategy.”
- Both are equal → “Your performance is stable. Try setting a slightly higher target for the next semester.”
For a first-semester student with only one SGPA, simply skip the trend advice because there is no previous semester to compare with.

This keeps the Academic Advisor simple while demonstrating conditions, arrays, comparisons, and decision-making—all appropriate for a beginner C project.