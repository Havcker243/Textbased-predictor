
# Text Frequency Analyzer Application

## Overview:

The Text Frequency Analyzer Application is a powerful tool designed to scrutinize text files for patterns in word usage. With this tool, users can delve deep into a text's contents, identifying common words and those that stand out due to their repetition.

### Key Features:

- **Frequency Calculation**: Determine the frequency of specific words within a file.
- **Top Word Identification**: Pinpoint the most commonly used word in a file.
- **Literary Analysis**: Gain insights into the predominant mood, theme, or tone by assessing word usage.

## Development Insights:

In constructing this application, the principles of object-oriented programming were applied to ensure modularity and scalability. Key data structures like maps and sets were harnessed for efficient data handling. The development journey also included mastering SDL, enhancing the application's overall quality.

## Instructions for Use:

1. **Setup**: Compile the program in your code editor. Ensure the e-book or text you aim to analyze is saved in the program's directory in a `.txt` format or plain text (UTF-8).
2. **Launch & Input**: Upon running, the application prompts for the text file's name (with extension). It will then request the 'N' frequency for word appearance.
3. **Analysis**: The program reads and processes the file — cleaning words of non-alphabetic characters and tallying word occurrences.
4. **Query**: Post-analysis, users can query words based on their frequency. The app displays all words occurring with the input frequency.

### Note:

The application is case agnostic. To streamline analysis, all words are converted to lowercase. Words delineated by whitespace are recognized, and non-alphabetic characters within words are stripped during the evaluation.

## Use Cases:

### 1. Analyzing Word Frequencies in a Book

- **Actor**: User
- **Goal**: Discern the frequency of each word in a book.
- **Preconditions**: The book's plain text file must be on hand.
- **Steps**:
  1. User provides the path to the plain text file.
  2. Application processes the file — breaking it down into individual words.
  3. Words are cleansed (e.g., lowercased, purged of punctuation).
  4. Word frequencies are logged and displayed in a structured table.

### 2. Analyzing Literary Works:

- **Description**: Writers or analysts might employ the tool to dissect an author's vocabulary spread in books or poetic anthologies. Such insights can reveal the author's stylistic tendencies.

  **Example**: A student, studying Shakespeare's "Romeo and Juliet" through the app, can discern primary motifs and themes by assessing frequently appearing words.

### 3. Identifying Trends in Research Articles:

- **Description**: Scholars and researchers can employ the Text Frequency Analyzer to glean insights from research papers, pinpointing popular keywords in their discipline.

  **Example**: A data scientist uses the tool to parse several AI research articles from the past year. Recognizing recurring terms, they glean insights about emergent technologies and methodologies trending in AI circles.
