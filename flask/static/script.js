// document.addEventListener("DOMContentLoaded", function() {
//     const searchBox = document.getElementById("search-box");
//     const clearIcon = document.getElementById("clear-icon");
//     const searchIcon = document.getElementById("search-icon");
//     const resultsContainer = document.getElementById("results");
//     const loading = document.getElementById("loading");

//     // Clear input when clicking the clear (cross) button
//     clearIcon.addEventListener("click", function() {
//         searchBox.value = "";
//     });

//     // Trigger search on Enter key press
//     searchBox.addEventListener("keypress", function(event) {
//         if (event.key === "Enter") {
//             searchArtists();
//         }
//     });

//     // Trigger search when clicking the magnifying glass
//     searchIcon.addEventListener("click", function() {
//         searchArtists();
//     });

//     function searchArtists() {
//         const query = searchBox.value.trim();
//         if (!query) {
//             alert("Please fill out this field.");
//             return;
//         }

//         resultsContainer.innerHTML = "";
//         loading.style.display = "block";

//         fetch(`/search?query=${query}`)
//             .then(response => response.json())
//             .then(data => {
//                 loading.style.display = "none";
//                 displayResults(data);
//             })
//             .catch(error => {
//                 console.error("Error fetching search results:", error);
//                 loading.style.display = "none";
//                 resultsContainer.innerHTML = "<p>Error fetching data.</p>";
//             });
//     }

//     function displayResults(data) {
//         resultsContainer.innerHTML = "";
//         if (data._embedded && data._embedded.results.length > 0) {
//             data._embedded.results.forEach(artist => {
//                 const artistCard = document.createElement("div");
//                 artistCard.classList.add("artist-card");

//                 const artistName = artist.title;
//                 const artistId = artist._links.self.href.split('/').pop();
//                 let imageUrl = artist._links.thumbnail?.href;

//                 if (!imageUrl || imageUrl.includes("missing_image.png")) {
//                     imageUrl = "/static/images/artsy_logo.svg";
//                 }

//                 artistCard.innerHTML = `
//                     <img src="${imageUrl}" alt="${artistName}" class="artist-image">
//                     <p>${artistName}</p>
//                 `;

//                 artistCard.addEventListener("click", () => fetchArtistDetails(artistId));
//                 resultsContainer.appendChild(artistCard);
//             });

//             resultsContainer.scrollLeft = 0;
//         } else {
//             resultsContainer.innerHTML = "<p>No results found.</p>";
//         }
//     }

//     function fetchArtistDetails(artistId) {
//         fetch(`/artist/${artistId}`)
//             .then(response => response.json())
//             .then(data => {
//                 document.getElementById("artist-name").textContent = `${data.name} (${data.birthday || ""} - ${data.deathday || ""})`;
//                 document.getElementById("artist-nationality").textContent = data.nationality || "";
//                 document.getElementById("artist-biography").textContent = data.biography || "";
//                 document.getElementById("artist-details").style.display = "block";
//             });
//     }
// });


// document.addEventListener("DOMContentLoaded", function() {
//     const searchBox = document.getElementById("search-box");
//     const clearIcon = document.getElementById("clear-icon");
//     const searchIcon = document.getElementById("search-icon");
//     const resultsContainer = document.getElementById("results");
//     const loading = document.getElementById("loading");
//     const artistDetails = document.getElementById("artist-details");

//     // Clear input when clicking the clear (cross) button
//     clearIcon.addEventListener("click", function() {
//         searchBox.value = "";
//     });

//     // Trigger search on Enter key press
//     searchBox.addEventListener("keypress", function(event) {
//         if (event.key === "Enter") {
//             searchArtists();
//         }
//     });

//     // Trigger search when clicking the magnifying glass
//     searchIcon.addEventListener("click", function() {
//         searchArtists();
//     });

//     function searchArtists() {
//         const query = searchBox.value.trim();
//         if (!query) {
//             alert("Please fill out this field.");
//             return;
//         }

//         // Clear previous search results and artist details
//         resultsContainer.innerHTML = "";
//         artistDetails.style.display = "none"; // Hide artist details on new search
//         loading.style.display = "block";

//         fetch(`/search?query=${query}`)
//             .then(response => response.json())
//             .then(data => {
//                 loading.style.display = "none";
//                 displayResults(data);
//             })
//             .catch(error => {
//                 console.error("Error fetching search results:", error);
//                 loading.style.display = "none";
//                 resultsContainer.innerHTML = "<p>Error fetching data.</p>";
//             });
//     }

//     function displayResults(data) {
//         resultsContainer.innerHTML = "";
//         if (data._embedded && data._embedded.results.length > 0) {
//             data._embedded.results.forEach(artist => {
//                 const artistCard = document.createElement("div");
//                 artistCard.classList.add("artist-card");

//                 const artistName = artist.title;
//                 const artistId = artist._links.self.href.split('/').pop();
//                 let imageUrl = artist._links.thumbnail?.href;

//                 if (!imageUrl || imageUrl.includes("missing_image.png")) {
//                     imageUrl = "/static/images/artsy_logo.svg";
//                 }

//                 artistCard.innerHTML = `
//                     <img src="${imageUrl}" alt="${artistName}" class="artist-image">
//                     <p>${artistName}</p>
//                 `;

//                 artistCard.addEventListener("click", () => fetchArtistDetails(artistId));
//                 resultsContainer.appendChild(artistCard);
//             });

//             resultsContainer.scrollLeft = 0;
//         } else {
//             resultsContainer.innerHTML = "<p>No results found.</p>";
//         }
//     }

//     function fetchArtistDetails(artistId) {
//         fetch(`/artist/${artistId}`)
//             .then(response => response.json())
//             .then(data => {
//                 document.getElementById("artist-name").textContent = `${data.name} (${data.birthday || ""} - ${data.deathday || ""})`;
//                 document.getElementById("artist-nationality").textContent = data.nationality || "";
//                 document.getElementById("artist-biography").textContent = data.biography || "";
//                 artistDetails.style.display = "block";
//             });
//     }
// });


document.addEventListener("DOMContentLoaded", function() {
    const searchBox = document.getElementById("search-box");
    const clearIcon = document.getElementById("clear-icon");
    const searchIcon = document.getElementById("search-icon");
    const resultsContainer = document.getElementById("results");
    const loading = document.getElementById("loading");
    const artistDetails = document.getElementById("artist-details");
    let activeCard = null;

    // Clear input when clicking the clear (cross) button
    clearIcon.addEventListener("click", function() {
        searchBox.value = "";
    });

    // Trigger search on Enter key press
    searchBox.addEventListener("keypress", function(event) {
        if (event.key === "Enter") {
            searchArtists();
        }
    });

    // Trigger search when clicking the magnifying glass
    searchIcon.addEventListener("click", function() {
        searchArtists();
    });

    function searchArtists() {
        const query = searchBox.value.trim();
        if (!query) {
            alert("Please fill out this field.");
            return;
        }

        // Clear previous search results and artist details
        resultsContainer.innerHTML = "";
        artistDetails.style.display = "none"; // Hide artist details on new search
        loading.style.display = "block";
        activeCard = null; // Reset active card

        fetch(`/search?query=${query}`)
            .then(response => response.json())
            .then(data => {
                loading.style.display = "none";
                displayResults(data);
            })
            .catch(error => {
                console.error("Error fetching search results:", error);
                loading.style.display = "none";
                resultsContainer.innerHTML = "<p>Error fetching data.</p>";
            });
    }

    function displayResults(data) {
        resultsContainer.innerHTML = "";
        if (data._embedded && data._embedded.results.length > 0) {
            data._embedded.results.forEach(artist => {
                const artistCard = document.createElement("div");
                artistCard.classList.add("artist-card");

                const artistName = artist.title;
                const artistId = artist._links.self.href.split('/').pop();
                let imageUrl = artist._links.thumbnail?.href;

                if (!imageUrl || imageUrl.includes("missing_image.png")) {
                    imageUrl = "/static/images/artsy_logo.svg";
                }

                artistCard.innerHTML = `
                    <img src="${imageUrl}" alt="${artistName}" class="artist-image">
                    <p>${artistName}</p>
                `;

                artistCard.addEventListener("click", () => {
                    fetchArtistDetails(artistId);
                    highlightCard(artistCard);
                });

                resultsContainer.appendChild(artistCard);
            });

            resultsContainer.scrollLeft = 0;
        } else {
            resultsContainer.innerHTML = "<p>No results found.</p>";
        }
    }

    function fetchArtistDetails(artistId) {
        fetch(`/artist/${artistId}`)
            .then(response => response.json())
            .then(data => {
                document.getElementById("artist-name").textContent = `${data.name} (${data.birthday || ""} - ${data.deathday || ""})`;
                document.getElementById("artist-nationality").textContent = data.nationality || "";
                document.getElementById("artist-biography").textContent = data.biography || "";
                artistDetails.style.display = "block";
            });
    }

    function highlightCard(card) {
        if (activeCard) {
            activeCard.classList.remove("active");
        }
        card.classList.add("active");
        activeCard = card;
    }
});


